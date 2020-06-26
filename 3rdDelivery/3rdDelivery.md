# 3rd Delivery 
## Comments
During the second delivery we recived an appreciation feedback on the project and also a critique on the mechanism that allows the projection of the hologram. 
We decided to test this with some potential users and we wanted to see if they had chosen to interact with the phone or objects. We took a sample of 15 people, divided in these age groups:
- 4 people between 11 and 14 now called 1st group
- 6 people between 15 and 24 now called 2nd group
- 5 people between 40 and 60 now called 3rd group
We chose the Think aloud method that is a user based evaluation method. In this technique, every user is encouraged to do a specific task and to comment what he/she is doing and why. 
At the end of the evaluation this is what came out: 
the first gruop preferred the object interaction mostly because they they thought this interaction was more playful and it seemed like a game. 
The second group was more toward the phone interaction because they think is more intuitive and says that your phone is always available but the object could be stolen or lost but the phone is  always in your pocket. Among 6 people 5 chose the phone and one the object.
The third group was even more divided between objects and phone. Three of them didn't want to download an application to interact with a statue in the museum and the other two wanted to try the object because they thought it was a different idea and they had not seen anything similar before. 
At the end of the testing we asked if they were more interested in the interaction with the phone if instead of an application we used a website, 11 out of 15 agreed. 

## Changes
After the second delivery we made minor changes to the project, since it was already mostly developed. We added some features and improved some techinal aspects.
## Design 
We decieded to make a competitor analysis to see if the idea was valid and we also changed the second persona under the advice of the Designer, Elisa. 
## Architecture
The architecture was stable but during the implementation of the new functionalities we decided to change some aspects to make the communication between the parts easier. We initially started working with a NoSQL database because we wanted to save files in a JSON format but while building the dashboard we found out that with an SQL database queries were more accurate. 
## Evaluation
The evaluation was expanded with a user based evaluation that we conducted. We defined some new KPI's  and did a Competitor Analysis. 
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