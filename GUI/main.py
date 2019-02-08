import sys
from PyQt5 import QtCore, QtWidgets, uic
from serial import Serial, SerialException

qtCreatorFile = r"C:\Users\User\My Files\Shark-O-Meter\GUI\sharkogui.ui"

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

class SerialReceiver(QtCore.QThread):
    signal = QtCore.pyqtSignal('PyQt_PyObject')
    serial = None

    def __init__(self, port, baudrate, timeout):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        QtCore.QThread.__init__(self)
        self.serial = Serial(self.port, baudrate=self.baudrate, timeout=self.timeout)

    def __del__(self):
        self.wait()

    def isConnected(self):
        return self.connected

    def run(self):
        try:
            while self.serial.is_open:
                self.connected = True
                ser_bytes = self.serial.readline()
                decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
                self.signal.emit(decoded_bytes)
            self.serial.close()
        except SerialException:
            print("Connection Lost.")

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    path_to_file = None

    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)

        self.connectButton.clicked.connect(self.connectionToggle)

        self.consoleSendEdit.returnPressed.connect(self.consoleSend)
        self.consoleSendButton.clicked.connect(self.consoleSend)

        self.downloadButton.clicked.connect(self.saveFileSelect)
        self.serialThread = None

    # Slots

    def fromSerial(self, data):
        self.appendToConsole(data + "\n")

    def connectionToggle(self):
        if self.serialThread and self.serialThread.serial.is_open:
            self.serialThread.serial.close()
            self.serialThread.quit()
            self.connectButton.setText("Connect")
        else:
            if (self.serialPortEdit.text() == '' or self.serialBaudEdit.text() == ''):
                QtWidgets.QMessageBox.information(self, "Needed Information", "Please supply a COM port number and baudrate.")
                return

            try:
                self.connectButton.setText("Connecting...")
                self.connectButton.setEnabled(False)
                self.serialThread = SerialReceiver(str(self.serialPortEdit.text()), int(self.serialBaudEdit.text()), 10)
                self.serialThread.signal.connect(self.fromSerial)
                self.serialThread.start()
                self.connectButton.setEnabled(True)
                self.connectButton.setText("Disconnect")
            except SerialException:
                self.connectButton.setEnabled(True)
                self.connectButton.setText("Connect")
                QtWidgets.QMessageBox.critical(self, "Connection Error", "Unable to connect to device. Check physical connection, COM port, and baudrate.")

    def consoleSend(self):
        self.toSerial(self.consoleSendEdit.text())
        self.appendToConsole(self.consoleSendEdit.text())
        self.consoleSendEdit.clear()

    def toSerial(self, text):
        self.appendToConsole(text)

    def appendToConsole(self, text):
        if text:
            cursor = self.consoleRecieveEdit.textCursor()
            cursor.movePosition(cursor.End)
            cursor.insertText(str(text))
            self.consoleRecieveEdit.ensureCursorVisible()

    def saveFileSelect(self):
        self.path_to_file = QtWidgets.QFileDialog.getSaveFileName(self, "Save As", "data.csv", filter="csv (*.csv)")
        self.serialThread.serial.write("!download")

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())
