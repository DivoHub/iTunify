# iTunify

Transfer playlists from your local iTunes library to Spotify

## Overview
This application parses the xml files of the user's local iTunes music library (Not to be confused with Apple Music), 
then iteratively queries the Spotify API using the data fetched from the xml file to find matching songs.
Songs are then appended to specified playlists on Spotify. Strength of matches can be adjusted while close/no matches are logged.




## Dependencies
- **Windows 10 or 11. (MacOs support tentative)**


- **Python V3.10** (or later)


- **requests**
  - License: Apache 2.0
  - [GitHub Repository](https://github.com/psf/requests)



## Usage
1. Clone Repo or download/unzip folder onto local machine

2. Install dependencies using PIP

```bash
pip install -r requirements.txt
```
---

## Contributing
Pull requests are welcome. Please specify fixes/changes.  
Telling me how trash the code is is also welcome

## License
[GPL-3](https://choosealicense.com/licenses/gpl-3.0/)


## Issues

- Unfinished
- MacOs support