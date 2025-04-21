let musicType = "SPOTIFY";
let cppOutput = localStorage.getItem('cppOutput') || "No Playlist Information"

function login() {
    window.location.href = "mainPage.html";
}

function waiting() {
  window.location.href = "waitingPage.html";
}

function musicTypeSpotify() {
    document.getElementById("Playlist_Field").placeholder="Paste The Link of Your Spotify Playlist";
    musicType = "SPOTIFY";
}

function musicTypeApple() {
    document.getElementById("Playlist_Field").placeholder="Paste The Link of Your Apple Music Playlist";
    musicType = "APPLE";
}


function getType() { // only allows for spotify right now
    return "SPOTIFY"

}

function submitPlaylist() {
    const playlist = document.getElementById('Playlist_Field').value;

    if (musicType == getType(playlist)) {
        sendPlaylist()
    }

}

function sendPlaylist() {
  const playlistField = document.getElementById('Playlist_Field');
  const playlist = playlistField.value;

  fetch('http://localhost:3000/send', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({ playlist, musicType })
  })
  .then(response => {
    if (!response.ok) {
      return response.json().then(errData => {
        throw new Error(`Error: ${errData.message}`);
      });
    }
    return response.json();
  })
  .then(data => {
    console.log('Server responded with:', data);

    if (data.code === 2) {
      alert('Error: Invalid Playlist or Spotify Issue');
    } else {
      localStorage.setItem('cppOutput', data.cppOutput);
      window.location.href = "playlistPage.html";
    }

    playlistField.value = "";
    playlistField.placeholder = "Enter another Spotify playlist URL...";
  })
  .catch(error => {
    console.error('Error:', error);
    alert(error.message);

    playlistField.value = "";
    playlistField.placeholder = "Please enter a valid Spotify playlist URL";
  });
}

function loadPlaylist() {
  let codes = cppOutput.split('|'); // Split the cppOutput string into an array
  let frameBase = "frame";

  for (let count = 0; count < codes.length; count++) {
    
    let frameId = frameBase + (count + 1); // e.g., frame1, frame2...
    let code = codes[count].trim(); // trim to remove extra spaces if any
    
    console.log(code);
    let frameElement = document.getElementById(frameId);
    if (frameElement) {
      frameElement.src = "https://open.spotify.com/embed/track/" + code + "?utm_source=generator";
    }
  }
}

window.addEventListener('DOMContentLoaded', () => {
  loadPlaylist();
});