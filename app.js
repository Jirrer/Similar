const express = require('express');
const cors = require('cors'); // Import cors
const { spawn } = require('child_process');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(cors()); // Enable CORS for all origins
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

app.post('/run-Python', (req, res) => {
  const pythonFileName = req.body.pythonFileName
  const data = req.body.data || [];
  const python = spawn('python', [path.join(__dirname, 'src', pythonFileName), ...data.map(String)]);

  let output = '';
  python.stdout.on('data', (data) => {
      output += data.toString();
  });

  python.stderr.on('data', (data) => {
      console.error(`Error from Python: ${data.toString()}`);
  });

  python.on('close', (code) => {
      console.log(`Python process exited with code ${code}`);
      res.json({ output }); // Send the Python output back to the frontend
  });
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});