import cv2
import pytesseract
import os


DIRECTORY = '../frames/'

# Get the list of all files and directories
path = DIRECTORY
dir_list = os.listdir(path)

pytesseract.pytesseract.tesseract_cmd = r'C:\Users\sergio\AppData\Local\Programs\Tesseract-OCR\tesseract.exe'


with open('ctf.txt', 'a') as fp:
    for i in dir_list:
        image = cv2.imread(DIRECTORY + i)
        text = pytesseract.image_to_string(image)
        fp.write("%s\n" % text)