from PyQt5 import QtWidgets, uic
import sys

#Load from UI file
application = QtWidgets.QApplication([])
frontend:QtWidgets.QMainWindow = uic.loadUi("frontend.ui")

#Bind program logic: Add ROM

def doAddRom(_):
    (path, _) = QtWidgets.QFileDialog.getOpenFileNames(frontend)
    if path != None and len(path) > 0:
        frontend.listRoms.addItem(path)

frontend.actionAddRom.triggered.connect(doAddRom)

#Bind program logic: Add core

def doAddCore(_):
    (path, _) = QtWidgets.QFileDialog.getOpenFileNames(frontend)
    if path != None and len(path) > 0:
        frontend.listCores.addItem(path)

frontend.actionAddCore.triggered.connect(doAddCore)

#Bind program logic: Start tests action

import tester
import multiprocessing, threading
testingThread:multiprocessing.Process = None
allowTesting = threading.Event()

def doStartTests(_):
    global testingThread
    if testingThread == None or not testingThread.is_alive():
        testingThread = multiprocessing.Process( \
            target=tester.smart_multi_test, \
            args=(\
                [frontend.listRoms .item(i).text() for i in range(frontend.listRoms .count())], \
                [frontend.listCores.item(i).text() for i in range(frontend.listCores.count())], \
                allowTesting \
            ))
        allowTesting.set()
        testingThread.run()
    else:
        msg = QtWidgets.QErrorMessage()
        msg.showMessage("Please wait for the current test set to finish, or abort them early (will destroy the data)!");
        msg.exec()

frontend.actionStartTests.triggered.connect(doStartTests);

#Bind program logic: Abort tests action

def doStopTests(_):
    global testingThread
    if testingThread != None and testingThread.is_alive():
        testingThread.kill()
    else:
        msg = QtWidgets.QErrorMessage()
        msg.showMessage("No tests are currently running!");
        msg.exec()

frontend.buttonAbortTests.clicked.connect(doStopTests);

#Bind program logic: Pause/resume tests action

def doPauseResumeTests(_):
    global testingThread
    if testingThread != None and testingThread.is_alive():
        if allowTesting.is_set():
            allowTesting.clear()
        else:
            allowTesting.set()
    else:
        msg = QtWidgets.QErrorMessage()
        msg.showMessage("No tests are currently running!");
        msg.exec()

frontend.buttonPauseResume.clicked.connect(doPauseResumeTests);

#Start execution
if __name__ == "__main__":
    frontend.show()
    sys.exit(application.exec())