import cv2

cam = cv2.VideoCapture(1)
while 1:
     _,frame =cam.read()
     cv2.imshow("features", frame)
     #if cv2.waitKey(10) == 0x1b: # ESC
     #    print 'ESC pressed. Exiting ...'
     #    break
     if cv2.waitKey(1) & 0xFF == ord('q'):

          cap.release()
          cv2.destroyAllWindows()
          break
     
