import cv2
import numpy as np

#img = cv2.imread('C:\Users\lenovo\Documents\gemma.jpg',3)

#print img.shape
 
#----
#boob = img[45:145, 60:145] # img[y1:y2,x1:x2]
#img[300:400,100:185] = boob
#cv2.imshow('boob',boob)
#-----
# Chow only blue and green< red == 0
#b = img[:,:,0]
#cv2.imshow('b',b)

img1 = cv2.imread('C:\Users\lenovo\Documents\gemma3-500x500.jpg',3)
img2 = cv2.imread('C:\Users\lenovo\Documents\gemma4-500x500.jpg',3)

dst = cv2.addWeighted(img1,0.7,img2,0.3,0)

cv2.imshow('dst',dst)


cv2.imshow('image1',img1)
cv2.imshow('image2',img2)
cv2.waitKey(0)
cv2.destroyAllWindows()
 