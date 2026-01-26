var http = require('http');
const fs=require('fs');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'});
 
 path ='./index.html';
  	 
   
  fs.readFile(path,(err,data)=>{
  if(err)
  {
	  console.log(err);
	  res.end();
  }
  else
  {
	res.end(data);  
  }
  })


}).listen(3000);