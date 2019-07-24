# UniPassau.WS

## Requirements

- `g++`
- `Knime`

## Structure

- `./*Presentation/` : Slides
- `./tech/` : Techncial Stuff
  - `./tech/knime.knwf` : Knime WorkFlow
  - `./tech/code/` : Source Code Files
  - `./tech/data/` : Data
    - `./tech/data/run/processed/` : Processed Numbers CSV Files
    - `./tech/data/run/train/` : Training Data
    - `./tech/data/run/test/` : Test Data
      - `./tech/data/run/*/gpx/` : Activitiy GPX Files
      - `./tech/data/run/*/knime/` : Stats CSV Files

## How to Run

- Change to tech/code/ directory : `cd tech/code`
- Build : `make`
- Run : `./main`

## How to Use

- Mode `{'train', 'test', '-1'}` :
  - `'train'` : Process File(s) as training
    - File Name `{'all', <fileName>, '-1'}` :
      - `'all'` :
        Process all the Files in : `./tech/data/run/train/gpx/`</br>
        Write all processed Files in : `./tech/data/run/processed/`</br>
        Append Stats to the CSV File : `./tech/data/run/train/knime/trainingData.csv`
      - `<fileName>` :
        Process the file : `./tech/data/run/train/gpx/<fileName>.gpx`</br>
        Write processed Numbers to the CSV File : `./tech/data/run/processed/<fileName>.gpx.csv`</br>
        Append Stats to the CSV File : `./tech/data/run/train/knime/trainingData.csv`
      - `"-1"` : Go Back to the previous Menu
  - `"test"` : Process Files as test Data
    - File Name `{<fileName>, '-1'}` :
      - `<fileName>` :
        Process the file : `./tech/data/run/test/gpx/<fileName>.gpx`</br>
        Write processed Numbers to the CSV File : `./tech/data/run/processed/<fileName>.gpx.csv`</br>
        Write Stats to the CSV File : `./tech/data/run/test/knime/<fileName>.gpx.csv`
      - `"-1"` : Go Back to the previous Menu
  - `"-1"` : Exit
