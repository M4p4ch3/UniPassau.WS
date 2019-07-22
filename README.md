# UniPassau.WS

## Structure

'./tech/' : Techncial Stuff
  './tech/code/' : Source Code Files
  './tech/data/' : Data

## Usage

Change to tech/code/ directory : 'cd tech/code'
Build : 'make'
Run : './main'

Mode :
  'train' : Fills the File : './tech/data/run/train/knime/trainingData.csv'
    FileName :
      'all' : Process all the files in : './tech/data/run/train/gpx/'
      <fileName> : Process the file : './tech/data/run/train/gpx/<fileName>.gpx'
  'test' : Fills the File : './tech/data/run/test/knime/<fileName>.gpx.csv'
    <fileName> : Process the file : './tech/data/run/test/gpx/<fileName>.gpx'
      
