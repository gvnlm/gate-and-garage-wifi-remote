const express = require('express');
const morgan = require('morgan');

const app = express();

app.use(morgan('tiny'));

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
