const express = require('express');
const cors = require('cors'); // Import cors
const { spawn } = require('child_process');
const path = require('path');

const app = express();
app.use(express.json());
const PORT = 3000;

app.use(express.urlencoded({ extended: true }));
app.use(express.static("public"));


function generatePlaylist(playlist, musicType, res) {
  if (musicType == "SPOTIFY") {
    const cpp = spawn('./src/FindSimilarSpotify');

    cpp.stdin.write(playlist);
    cpp.stdin.end();

    cpp.stdout.on('data', (data) => {
      console.log(`From C++: ${data.toString()}`);
    });
    
    cpp.stderr.on('data', (data) => {
      console.error(`C++ Error: ${data.toString()}`);
    });
    
    cpp.on('close', (code) => {
      console.log(`C++ process exited with code ${code}`);

      if (code === 2) {
        res.status(400).json({ message: 'Invalid Playlist or Spotify Issue', code: 2 });
      } else {
        res.json({ message: 'Playlist generated successfully', code: code });
      }
    });
    
  }
}

app.post('/send', (req, res) => {
  const { playlist, musicType } = req.body;
  console.log('Received:', playlist, musicType);

  // Only send response inside generatePlaylist
  generatePlaylist(playlist, musicType, res);
});


app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});