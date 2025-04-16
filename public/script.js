let musicType = "SPOTIFY";

function login() {
    window.location.href = "mainPage.html";
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

function sendPlaylist() { // need to still check if its real url
    const playlist = document.getElementById('Playlist_Field').value;

    fetch('http://localhost:3000/send', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({ playlist, musicType })
    })
    .then(response => response.json())
    .then(data => {
      console.log('Server responded with:', data);
    });
  }
