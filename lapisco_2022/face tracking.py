import cv2

cap = cv2.VideoCapture(0)

v_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
v_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

video_name = 'this is your face' + '.mp4'

writer = cv2.VideoWriter(
    video_name, cv2.VideoWriter_fourcc(*'mp4v'), 20, (v_width, v_height))

# Toggle recording
record = False

# Press `esc` to exit
while cv2.waitKey(1) != 27:
    _, frame = cap.read()

    classifier = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

    bounds = classifier.detectMultiScale(frame)

    for box in bounds:
        x, y, b_width, b_height = box
        cv2.rectangle(frame, (x, y), (x+b_width, y+b_height), (0, 255, 0), 2)

    cv2.imshow(video_name[:-4], frame)

    if record == True:
        writer.write(frame)


cap.release()
writer.release()
cv2.destroyAllWindows()
