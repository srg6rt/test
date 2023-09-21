# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import cv2
import numpy as np
import os


def find_image(path):

    # Read the main image
    img_rgb = cv2.imread(path)

    # Convert it to grayscale
    img_gray = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)

    # Read the template
    template = cv2.imread('pattern.png', 0)

    # Store width and height of template in w and h
    w, h = template.shape[::-1]

    # Perform match operations.
    res = cv2.matchTemplate(img_gray, template, cv2.TM_CCOEFF_NORMED)

    # Specify a threshold
    threshold = 0.9

    # Store the coordinates of matched area in a numpy array
    loc = np.where(res >= threshold)

    if str(loc[0]) == '[]':
        print("NOT Detected")
        os.remove(DIRECTORY + path)

    else:
        print("Detected")

    # Draw a rectangle around the matched region.
    for pt in zip(*loc[::-1]):
        cv2.rectangle(img_rgb, pt, (pt[0] + w, pt[1] + h), (0, 255, 255), 2)

    # Show the final image with the matched area.
    #cv2.imshow('Detected', img_rgb)

    # waits for user to press any key
    # (this is necessary to avoid Python kernel form crashing)
    #cv2.waitKey(0)

    # closing all open windows
    #cv2.destroyAllWindows()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    DIRECTORY = '../frames/'

    # Get the list of all files and directories
    path = DIRECTORY
    dir_list = os.listdir(path)

    #print("Files and directories in '", path, "' :")

    # prints all files
    #print(len(dir_list))

    for i in dir_list:
        find_image(DIRECTORY + i)

