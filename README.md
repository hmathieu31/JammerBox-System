# PIR

PIR Project

<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <h1>PIR PROJECT</h1>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#functionalities">Functionalities</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

Our PIR Project consisted in upgrading the existing Jammer Box System from Vitesco. The previous system used a microchip to jam the CRK and CAM signals, and used a terminal as an interface for the system.

Our team decided to use a newer system : the RaspberryPi, combined with a Nucleo STM32. This can allow us to store data more easily and make a better interface for the Jammer box. We could also inject faults without being directly connected to the RaspberryPi.

//TO DELETE Here's why:

- Your time should be focused on creating something amazing. A project that solves a problem and helps others
- You shouldn't be doing the same tasks over and over like creating a README from scratch
- You should implement DRY principles to the rest of your life :smile:
  //

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

This section should list any major frameworks/libraries used to bootstrap your project. Leave any add-ons/plugins for the acknowledgements section. Here are a few examples.

- [Next.js](https://nextjs.org/)
- [React.js](https://reactjs.org/)
- [Vue.js](https://vuejs.org/)
- [Angular](https://angular.io/)
- [Svelte](https://svelte.dev/)
- [Laravel](https://laravel.com)
- [Bootstrap](https://getbootstrap.com)
- [JQuery](https://jquery.com)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

After connecting connecting the RaspberryPi to the STM32, some requirements is needed before running a web server on the RaspberryPi.

### Prerequisites

Some things has to be installed in the RaspberryPi before importing our project code. It is firstly necessary to configure the wi-fi or connect the RaspberryPi to internet through an ethernet cable to be able to install the required modules.

//IL FAUT PARLER DE COMMENT CONFIGURER INTERNET ETC...

For the installation, you can either be connected directly to the device, or connect through ssh with another machine with the command :

```sh
ssh [IP adress of RaspberryPI]
```

\_NB : You have to be connected to the same network as the device.

Here is the two modules that are needed to be installed on the RaspberrPi :

- node
- npm

Those two modules can be installed at the same time following the instructions on this website [https://www.instructables.com/Install-Nodejs-and-Npm-on-Raspberry-Pi/](https://www.instructables.com/Install-Nodejs-and-Npm-on-Raspberry-Pi/)

### Installation

After installing all of the requirements, you can now install our project on the device through git and then configure it.

1. Clone the repo
   ```sh
   git clone git@github.com:hmathieu-insat/PIR.git
   ```
2. Get to the repo
   ```sh
   cd /PIR
   ```
3. Configure the project
   ```sh
   chmod u+x Congigure.sh
   ./Configure.sh
   ```
4. A prompt for installing Powershell will appear, type in what you want to do (yes/no)

5. Wait until installation is complete (this may take a while)

<br/>

Before running the project, modify the //INSERER NOM DE FICHIER// that is situated in the //DOSSIER // in order to write in the field :

```json
{
  "IP ADRESS": "IP address of the device"
}
```

The web server can finally run properly in the device with the command:

```sh
chmod u+x Run.sh
./Run.sh
```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

## Usage

Every machine can now visit the web site hosted by the RaspberryPi if they are connected to the same network. In a web browser, type in this link http://[IP adress of RaspberryPi]:3000/.

You will land on the starting page of the web site, and from there, you can use all of the functionnalities displayed.

<!-- INTERFACE WEB FUNCTIONALITIES -->

## Functionalities

### Inject fault

Allows to inject one of the following faults into the Jammer Box for testing if it detects the fault and reacts accordingly to it.

- CRK SHORT CIRCUIT 
- CAM SHORT CIRCUIT 
- CRK SPK
- CRK RUN OUT
- CRK TOOTH OFF
- CRK GAP NOT DET
- CRK SEG ADP ERR LIM
- CRK PULSE DURATION
- CRK POSN ENG STST
- CAM DELAY
- CAM SPK
- CAM PAT ERR

If a parameter is necessary, another small window will open allowing the introduction of this value and then the start of the jamming. When a parameter is not valid, a pop up window will show informing the user of this. If no parameters are needed, the jamming will start immediately after pressing the corresponding fault button. For either case, when the jamming starts, another pop up window will show up informing the user of the success of the order.

### Faults Injection Logs

Allows to inspect the faults historic logs. Each time a new fault is injected, this page will update and show its characteristics as well as if it was correctly executed. This is done by reading a JSON file that the API updates every time a new fault is injected. In addition, there is a delete button that cleans the faults log when pressed.

Each fault has a replay button, replaying the jammering with the same characteristics as before.


### Configuration

When the “Upload config” button is pressed, a window will open for searching in the user computer a JSON file with the Jammer Box configuration. For example:

```JSON
{
  "NumOfTeeth": 60,
  "NumOfGap": 1,
  "NumOfTeethInGap": 2,
  "Tdc0": 87.75,
  "FirstErSegAngle": 42,
  "NumOfCylinder": 4,
  "CrkSensorType": "c",
  "Cam0NumOfEdges": 2,
  "Cam0Active_edge": "b",
  "Cam0SensorType": "c",
  "Cam0FilterInMicroSec": 30,
  "Cam0EdgePos": 0.333
}
```



Once this file is uploaded, the user can choose to configure the CAM or the CRK separately. With the reset button, either one of these configurations can be erased.

### Start recording

When pressed, it starts recording and saving in file the signals from the Jammer Box for further analysis.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

- Aubut, Guillaume - aubut@insa-toulouse.fr
- Mancinelli, Alejo - mancinel@insa-toulouse.fr
- Mathieu, Hugo - hmathieu@insa-toulouse.fr
- Mouton, Viktor Adrian - vmouton@insa-toulouse.fr
- Omre, Erik Semb - omre@insa-toulouse.fr
- Pastor, Emmanuel - e_pastor@insa-toulouse.fr
- Sixt, Romain - sixt@insa-toulouse.fr

Project Link: [https://github.com/hmathieu-insat/PIR](https://github.com/hmathieu-insat/PIR)

<p align="right">(<a href="#top">back to top</a>)</p>
