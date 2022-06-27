import cv2
import numpy as np
import colorsys as cs

cap = cv2.VideoCapture(0)

width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

video_name = 'this is your object' + '.mp4'

writer = cv2.VideoWriter(
    video_name, cv2.VideoWriter_fourcc(*'mp4v'), 20, (width, height))

# Toggle recording
record = False

# Press `esc` to exit
while cv2.waitKey(1) != 27:
    _, frame = cap.read()

    hsv_image = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Base RGB values close to object were taken from google
    base_rgb = [7/255, 51/255, 110/255]
    base_hsv = cs.rgb_to_hsv(base_rgb[0], base_rgb[1], base_rgb[2])

    # Trial and error variables for good coverage
    h, s, v = base_hsv[2]*255, 50, 50
    displacement = 20

    # Mask applying for selective show
    lower_bound = np.array([h-displacement, s, v])
    upper_bound = np.array([h+displacement, 255, 255])
    mask = cv2.inRange(hsv_image, lower_bound, upper_bound)
    frame = cv2.bitwise_and(frame, frame, mask=mask)

    cv2.imshow(video_name[:-4], frame)

    if record == True:
        writer.write(frame)


cap.release()
writer.release()
cv2.destroyAllWindows()
