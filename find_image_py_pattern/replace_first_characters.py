import cv2
import os


DIRECTORY = '../frames/'

# Get the list of all files and directories
path = DIRECTORY
dir_list = os.listdir(path)

with open('CLF-02.txt', 'a') as fp1:
    with open('ctf.txt', 'r') as fp:
        first_line_idx = 0
        Lines = fp.readlines()
        for idx, i in enumerate(Lines):
            for j in range(180, 870):
                if str(j)+")" in i[:5] or str(j)+" )" in i[:5]:
                    first_line_idx = idx

                    number_and_first_sentence = ("Q"+i).split(')', 1)
                    fp1.write("%s\n" % number_and_first_sentence[0])
                    fp1.write("%s" % number_and_first_sentence[1])
                    #print(number_and_first_sentence[0])
                    #print(number_and_first_sentence[1], end="")

            if Lines[first_line_idx] in i:
                pass
            else:
                fp1.write("%s" % i)
                print(i, end="")
