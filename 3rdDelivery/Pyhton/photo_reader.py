import os.path
from os import path
import cv2
import requests  # to get image from the web
import shutil  # to save it locally
import os

filename = "gc"
compression = "jpg"
img_url = "https://statues-iot.s3.eu-west-3.amazonaws.com/{}.{}".format(
    filename, compression
)
local_path = "./photo/" + filename

if path.exists(local_path):
    print("Image present locally")
    img = cv2.imread(local_path)
    cv2.imshow("image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
else:
    r = requests.get(img_url, stream=True)
    if r.status_code == 200:
        print("Image sucessfully downloaded: ", filename)
        # Set decode_content value to True, otherwise the downloaded image file's size will be zero.
        r.raw.decode_content = True
        with open("./photo/{}".format(filename), "wb") as f:
            f.write(r.content)
        img = cv2.imread(local_path)
        cv2.imshow("image", img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    else:
        print("Image {} not downloaded, error {}".format(filename, r.status_code))


"""
s3 = boto3.resource('s3', region_name='us-east-2')
bucket = s3.Bucket('sentinel-s2-l1c')
object = bucket.Object('image.jpg')
tmp = tempfile.NamedTemporaryFile()
"""

