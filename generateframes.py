import cv2
import os
import math
counter = 0
videofolder = "scissor_videos"
positivefolder = "positive_pictures/imgs"
negativefolder= "negative_pictures/imgs"
backgoundvideo= "./back.mp4"
datafolder="pictures"

maxsize = 300*300
dirs = os.listdir("./"+videofolder)
datlog = open(datafolder+"/"+"scissors.dat", 'w')
for file in dirs:
    cap = cv2.VideoCapture("./"+videofolder+"/"+file)
    flag = cap.isOpened()
    while(flag):
        flag, frame = cap.read()
        if flag:
            nowsize = frame.shape[1] * frame.shape[0]
            if nowsize > maxsize:
                height = round(frame.shape[0] * math.sqrt(maxsize / nowsize))
                width = round(frame.shape[1] * math.sqrt(maxsize / nowsize))
                frame = cv2.resize(frame, (width, height))
            cv2.imshow("now writing", frame)
            cv2.imwrite("./"+datafolder+"/"+positivefolder+"/"+str(counter)+".jpg",frame)
            datlog.write(positivefolder+"/"+str(counter)+".jpg"+" 1 0 0 "+str(frame.shape[1])+" "+str(frame.shape[0])+"\n")
            counter = counter+1
            cv2.waitKey(1)

cap = cv2.VideoCapture(backgoundvideo)
flag = cap.isOpened()
counter=0
datlog = open(datafolder+"/"+"background.dat", 'w')
while(flag):
    flag, frame = cap.read()
    if(flag):
      cv2.imshow("now writing", frame)
      cv2.imwrite("./" +datafolder+"/"+ negativefolder + "/" + str(counter) + ".jpg", frame)
      datlog.write(negativefolder + "/" + str(counter) + ".jpg"+"\n")
      counter=counter+1
      cv2.waitKey(1)