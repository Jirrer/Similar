const http = require('http');
const { spawn } = require('child_process');

// Create HTTP server
const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello, World!\n');
});

server.listen(3000, 'localhost', () => {
  console.log('Server running at http://localhost:3000/');
});

// Data to pass to Python script
const data = [1, 4]; // Sample data, can be dynamically passed

// Spawn Python process
const python = spawn('python', ['src/FindSimilarSongs.py', ...data.map(String)]);

// Handle output from Python
python.stdout.on('data', (data) => {
  console.log(`Output from Python: ${data.toString()}`);
});

// Handle errors (if any)
python.stderr.on('data', (data) => {
  console.error(`Error from Python: ${data.toString()}`);
});

// Handle Python process exit
python.on('close', (code) => {
  console.log(`Python process exited with code ${code}`);
});
