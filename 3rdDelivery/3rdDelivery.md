# 3rd Delivery 
## Comments

During the second delivery we received positive comments, related to the project idea and the use of iot, and we were very pleased, considering that we had started from scratch with a new idea.

The main criticisms we received were:
-1 The fact that it didn't make much sense that the hologram wasn't always visible but that it needed user interaction to make it appear.

-2 The evaluation document was incomplete, did not follow the previous document and did not accurately describe how to do experiments with users.

-First comment:
We decided to insert the interaction because in the preliminary interviews with users it had emerged that they would have preferred to "play", for example choosing the right object for the statue, instead of passively looking at the hologram.
However, we decided to investigate even deeper and experiment with users to see if they actually preferred to interact or not.
We had 8 users test our product and divided them into 2 groups of 4 people.
The first group tested the product first by interacting with the board and then seeing the projected hologram directly without having to do anything.
The second did the opposite, first testing the projected hologram constantly and then the interaction with the board.

At the end of the experiment we asked all the users what they preferred to do, and only 1 user answered that he would have preferred to see the hologram already projected without the need for interaction.

So we decided to keep the interaction with the users in our project.

-Second comment:
In this case we decided to try to have more continuity between the documents and above all to be more careful in explaining the experiments done with the users.
   

## Changes
After the second delivery we made minor changes to the project, since it was already mostly developed. We added some features and improved some techinal aspects.
## Design 
We decieded to change the second persona under the advice of the Designer, Elisa. 
## Architecture
The architecture was stable but during the implementation of the new functionalities we decided to change some aspects to make the communication between the parts easier. We initially started working with a NoSQL database because we wanted to save files in a JSON format but while building the dashboard we found out that with an SQL database queries were more accurate.
## Evaluation
The evaluation was expanded with a user based evaluation that we conducted and also We defined some new KPI's and did a Competitor Analysis to search some possible competitors and compare our product with them. 
## Brief presentation of the technical work done since the 2nd delivery
Since the 2nd delivery we imlemented the following features: 
- Set up the SQL database
- Created an S3 bucket to store images
- Created a script to donwload the image if isn't in the main memory and that shows the image
- Created a dashboard to inform curators about the frequency of activaction of a statue
- Lambds function to save MQTT messages inside the Database
- Updated the code of the board to MbedOS 6 

## Brief presentation of the evaluation conducted since the 2nd delivery
- Competitor anlysis
- Think aloud evaluation
- Possibility to implement an application instead of using objects
- Latency of the image with a new library
## A brief list of the functionality that is still missing and that we did not manage to evaluate.
- 
