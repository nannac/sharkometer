import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic

qtCreatorFile = r"C:\Users\User\My Files\Shark-O-Meter\GUI\sharkogui.ui"

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):

    path_to_file = ""

    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)

    def selectFile():
        return QFileDialog.getOpenFileName()

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

    #self.path_to_file = self.downloadButton.clicked.connect(selectFile)
    print("self.path_to_file")
