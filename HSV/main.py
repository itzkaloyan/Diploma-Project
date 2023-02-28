import cv2
import numpy as np

image = cv2.imread("/home/student1/code/JetBot/HSV/test_images/8f.jpg")
cv2.imshow("Original", image)

result = image.copy()

image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

lower = np.array([0, 5, 50])
upper = np.array([179, 50, 255])

lower_mask = cv2.inRange(image, lower, upper)

result = cv2.bitwise_and(result, result, mask=lower_mask)

cv2.imshow('mask', lower_mask)
cv2.imshow('result', result)

cv2.waitKey(0)
cv2.destroyAllWindows()

