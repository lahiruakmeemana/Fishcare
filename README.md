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

![image](https://user-images.githubusercontent.com/58099828/128254217-4169d257-2eeb-4c3c-a08b-a59d92ea2717.png)
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
8 most common diseases among aquarium fish are considered due to lack of data availability. 18 common fish breeds are inditified which are fallen ill to these diseases. which are listed in `Fish_breeds.txt` and `Diseases.txt`

## Implementation
