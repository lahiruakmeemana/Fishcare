# Fishcare
Fish classification and disease detection 

## Project Description
Fishkeeping is a hobby, concerned with keeping fish in a home aquarium or garden pond. There is also a fishkeeping industry, as a branch of agriculture. Broadly fishkeeping can be divided into two categories
- Freshwater fishkeeping
- Saltwater fishkeeping

As freshwater fishkeeping is the mainstream in Sri Lanka, the scope of this project will cover only freshwater fishkeeping.
One of the main concerns of a common fish keeper is lack of knowledge about the fish diseases and proper treatments for them. They know that thier fish are by looking at them but they do not know what is the disease or what are the treatments. The goal of this project is to address this problem by developing a system which can classify fish breeds and, detect and recognize diseases, and giving instructions to keep an healthy environment for thier fish by inspecting water conditions. 

### How to detect diseases/ Symptoms of diseases
- Color changes or abnormalities in skin, eyes, gills, fins of a fish
- Lack of apetite
- Less movements or odd swimming behaviour
- Sinking or floating too much

  ![image](https://user-images.githubusercontent.com/58099828/128254151-35116b31-780f-460c-8378-fca8d3d4a70e.png)

### Water condition
One of the main reason for fish diseases is the condition of the water. THe ideal water conditions are displayed in the following table. Changes in water conditions cause parasites, bacteria and varoius other things to grow, and some rise of these conditions(eg: Ammonia) are toxic to fish and cause diseases. 

  ![image](https://user-images.githubusercontent.com/58099828/128254217-4169d257-2eeb-4c3c-a08b-a59d92ea2717.png)<br/>
  from https://www.aqueon.com/articles/freshwater-aquarium-water-quality

## System design
The proposed system consists of two componenets
- A sensor node
  - The sensor node consists of sensors to measure the water condition and fixed at the home aquarium.
- An Android app
  - The app takes photos and does the detection and classification and also communicates with the sensor node to get the water condition measurements.
### Inspected symptoms
Color changes and abnormalities of the fish are only considered.
  Since only an image is used for detection and classification, other symptoms listed before cannot be detected.
### Water conditions to be considered
Not all of the condtions listed above cannot be measured using sensor modules. Some of them need to be measured using specific kits. Therefore only **temperature, pH level, Total dissolved solids count, and turbidity( clearness of the water)** is cosidered. 
### Fish breeds and diseases
8 most common diseases among aquarium fish are considered due to lack of data availability. 17 common fish breeds are inditified which are fallen ill to these diseases. which are listed in `Fish_breeds.txt` and `Diseases.txt`

## Implementation

### Data
Data gathered from Google Images, various Facebook groups and pages, and aquarium community websites. Enough data for fish breed classification can be collected but data for diseases are hard to acquire.
Data colleted till now,
- Fish breeds: 1670
- Diseases: 289
More data will be gathered as the project goes on.

### Sensor node
**Temperature sensor, pH sensor, turbidity sensor, and TDS sensor** are included along with **ESP32** microcontroller. <br/>ESP32 is selected due to its small size, enough processing power, and Bluetooth and Wifi availability. <br/>
![nodemcu-esp32](https://user-images.githubusercontent.com/58099828/128307333-e089c246-d157-439c-8022-54a8da8767b8.jpg)

- Temperature sensor <br/>
  ![temperature](https://user-images.githubusercontent.com/58099828/128306920-1fe1ff5c-5bdf-4a8b-869d-da47a248acd9.jpeg)

- pH sensor <br/>
  ![ph](https://user-images.githubusercontent.com/58099828/128306926-4fcc8d8f-5a74-49ff-a459-b2dac89308fe.jpg)

- Turbidity sensor <br/>

  ![turbidity](https://user-images.githubusercontent.com/58099828/128306934-9520d679-d163-47b4-8d98-ae5ac7a02c98.jpg)
  ![schem](https://user-images.githubusercontent.com/58099828/128307841-72dc4626-e5ef-4ac7-bd66-23556a2f695c.png)<br/>
  In case of a failure to find a sensor module, a basic sensor can be made using following circuit<br/>

- TDS sensor <br/>
 
  ![tds](https://user-images.githubusercontent.com/58099828/128306947-9c8c16ca-9b9d-4fac-9e7e-f5d8ea3bddb6.png)
  ![ol2eccircuit](https://user-images.githubusercontent.com/58099828/128308328-2bca4169-e3de-4477-8d90-5814e7dce6e2.jpg)<br/>
  Basic sensor circuit<br/>
  
  **For the demonstration, only a temperature sensor is used due to lack of availability of sensors and low accuracy of sensors built using basic circuits.**
  
 Temperature data is collected as in the following format. ESP32 wakes up every 15 minutes and sends collected temperature data to firebase realtime database.<br/>
![Annotation 2021-09-22 224820](https://user-images.githubusercontent.com/58099828/134392600-399ea873-41ad-4963-a6cd-664398c448d7.jpg)


### Data Labeling
![boundingbox](https://user-images.githubusercontent.com/58099828/129083468-037d61e1-32fd-451d-9c17-ca485d0ca21f.jpg)
![polygon](https://user-images.githubusercontent.com/58099828/129083474-6b6e5c65-5970-484b-a9d9-f6dd2735b2a2.jpg)

Above two approaches are to be tested on few fish breeds and the one gives best resutls will be used to label all the data.

A simple CNN is built to classify 3 fish breeds using *bounding box* annotation. Below graphs describe traning accuracies of the model.<br/>
![Annotation 2021-08-18 111655](https://user-images.githubusercontent.com/58099828/129844229-07853098-4912-4996-bacc-280014c80828.jpg)
![Annotation 2021-08-18 111708](https://user-images.githubusercontent.com/58099828/129844236-9bfcb0d7-72f0-420e-819a-3485c13a99c6.jpg) <br/>
Considerable accuracy is acquired with few epochs. Validation accuracy varies because of less data.
Based on the results and content of following paper, Bounding box labeling is selected to train the model.
> J. F. Mullen, F. R. Tanner and P. A. Sallee, “Comparing the Effects of Annotation Type on Machine Learning Detection Performance,” 2019 IEEE/CVF Conference on Computer Vision and Pattern Recognition Workshops (CVPRW), 2019, pp. 855-861, doi: 10.1109/CVPRW.2019.00114.

### Classification
Fish classification implemented using a CNN. As the accuracy was very low, already avaible network is considired to be used as feature extractor.
Currently working on using ResNet50.

## TimeLine <br/>
![image](https://user-images.githubusercontent.com/58099828/129842766-a49af1f9-2eda-48f3-b019-3a30ff11fc5e.png) <br/>

## Weekly Updates

### Week 1

- Started collecting data for Fish and disease classification. <br/>
  - *Sources*: <br/>
    https://www.google.com/imghp?hl=EN <br/>
    https://www.facebook.com/groups/AquariumKeepers69/?multi_permalinks=2744512122517463c <br/>
    https://www.facebook.com/groups/FishTankEnablers/?multi_permalinks=1239240096489399 <br/>
    https://www.facebook.com/groups/Carpnado/?multi_permalinks=3042710135972472 <br/>
    https://www.facebook.com/groups/bettakeepers/?multi_permalinks=356133915965277 <br/>
    https://www.facebook.com/groups/154362351866569/?multi_permalinks=805873170048814 <br/>
    https://www.facebook.com/groups/132870007364711/ <br/>
    https://www.facebook.com/groups/1509542092636185/?multi_permalinks=2961202860803427 <br/>
    https://www.myaquariumclub.com/search.html?search_req=search&searchword=photo <br/>
- Read exsisting solutions research papers
	- Fish-Pak: Fish Species Dataset from Pakistan for Visual Features Based Classification: https://data.mendeley.com/datasets/n3ydw29sbz/3 <br/>
	- Fish Disease Detection Using Image Based Machine Learning Technique in Aquaculture: https://www.sciencedirect.com/science/article/pii/S1319157821001063 <br/>
	Image processing technique to detect fish disease: https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.736.9131&rep=rep1&type=pdf <br/>

### Week 2

- Started Fish data labeling <br/>
	 - As said above only few breeds are labeled first and test it on classification to select the optimal way.<br/>
- Started learning Flutter for developping the app.
- Started implementing sensor node.

### Week 3
- Basic sensor node code is implemented. <br/>
![temp test](https://user-images.githubusercontent.com/58099828/129843450-278245d5-26ae-42b6-b6ec-ea663aac5071.jpg) <br/>
![IMG_20210818_005850](https://user-images.githubusercontent.com/58099828/129843511-602a3297-1742-4ad7-ac4b-11b4a87d7278.jpg) <br/>
- A simple CNN is built and tested on 3 fish breeds. As explained in **Data labeling** bounding box annotation is used on the remaining data. 

### Week 4
- Disease data collecting. 350 images collected from above mentioned sources.
- Learning flutter basics.

### Week 5
- Started developing the app.
- Sensor node timer and sleep implemented.
	- 15 minutes timer is set. Node wakes up and measures temperature.

### Week 6
- Firebase database is created to store temperature data. 
	- Node sends data to firebase database every 15 minutes. 
- Started working on fish classification.

### Week 7
- Implementing a CNN using already available backend eg. ResNet50,VGG16
	- After 5 iterations: <br/>
	![image](https://user-images.githubusercontent.com/58099828/134411848-ef681544-78c1-4afc-b384-4cafd94a3014.png)

### Week 8
- Temperature data visualized and observed daily patterns
	![image](https://user-images.githubusercontent.com/58099828/137205751-e3e483e4-9d2f-4e31-b02c-342221c663d3.png)

### Week 9
- Facebook Prophet is used to forecast temperature readings.
	- This was just to get an idea on how to do the prediction. In the final system, prediction model is trained on the app and predict future parameters.
	![image](https://user-images.githubusercontent.com/58099828/137205989-c2fcbca1-17dd-419a-a5f0-a354c2afda35.png)

### Week 10
- Firebase connection implemented in the app.
- Trained classification model run on app.
