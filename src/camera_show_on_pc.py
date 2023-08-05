import cv2

stream_url = "http://192.168.100.19:81/stream"

cap = cv2.VideoCapture(stream_url)

# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')
output_file = "output_video.avi"
fps = 20
frame_width = int(cap.get(3))
frame_height = int(cap.get(4))
out = cv2.VideoWriter(output_file, fourcc, fps, (frame_width, frame_height))

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Save frame to the output file
    out.write(frame)

    cv2.imshow("ESP32 Camera Stream", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
out.release()
cv2.destroyAllWindows()
