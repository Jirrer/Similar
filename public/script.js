submittedPlaylist = [] // needs to be sumbitted

function getSubmittedPlaylist() {
    return submittedPlaylist;
}

function submitPlaylist(playlist) {
    submittedPlaylist = playlist;
}

async function findNewSongs(pythonFileName) {
    try {
        const response = await fetch('http://localhost:3000/run-python', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ // Send data to the backend
                pythonFileName: pythonFileName,
                data: getSubmittedPlaylist()
            }), 
        })

        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        const result = await response.json();
        return result.output;
    } catch (e) {
        console.error('Error:',e)
        return 'Error returning .py file'
    }
}


async function updateText() {
    const output = await findNewSongs('FindSimilarSongs.py')
    document.getElementById('output').innerText = output
}