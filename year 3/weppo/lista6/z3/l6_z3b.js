var http = require("http");
var express = require("express");
var session = require('express-session');
var FileStore = require('session-file-store')(session);

var app = express();

app.use(session({
    store: new FileStore,
    secret: 'keyboard cat',
    resave: true,
    saveUninitialized: true
  })
);

app.use('/', function (req, res) {
  if (req.session.views) {
    req.session.views++;
    res.setHeader('Content-Type', 'text/html');
    res.write('<p>views: ' + req.session.views + '</p>');
    res.end();
  } else {
    req.session.views = 1;
    res.end('Welcome to the file session demo. Refresh page!');
  }
});

http.createServer(app).listen(3000);

