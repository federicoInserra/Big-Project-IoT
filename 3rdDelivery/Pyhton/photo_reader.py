import os.path
from os import path
import cv2
import requests  # to get image from the web
import shutil  # to save it locally

img_url = "https://www.turismo.it/typo3temp/pics/56efd8576b.jpg"
filename = img_url.split("/")[-1]
photopath = "./photo/" + filename

if path.exists(photopath):
    print("File is in cache")
    print("Opening image")
    img = cv2.imread(photopath)
    cv2.imshow("image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
else:
    print("downloading image")
    r = requests.get(img_url, stream=True)
    if r.status_code == 200:
        print("Image sucessfully Downloaded: ", filename)
        # Set decode_content value to True, otherwise the downloaded image file's size will be zero.
        r.raw.decode_content = True
        with open("./photo/{}".format(filename), "wb") as f:
            f.write(r.content)
        print("opening image")
        img = cv2.imread(photopath)
        cv2.imshow("image", img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    else:
        print("Image Download Failed: ", filename)


"""
s3 = boto3.resource('s3', region_name='us-east-2')
bucket = s3.Bucket('sentinel-s2-l1c')
object = bucket.Object('image.jpg')
tmp = tempfile.NamedTemporaryFile()
"""

