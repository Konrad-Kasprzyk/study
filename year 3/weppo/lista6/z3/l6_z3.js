var http = require("http");
var express = require("express");
var session = require("express-session");
var bodyParser = require("body-parser");
var cookieParser = require('cookie-parser');

var app = express();

app.set("view engine", "ejs");
app.set("views", "./views");
app.disable("etag");

app.use(bodyParser.urlencoded({ extended: true }));
app.use(cookieParser());

app.use(
  session({
//Forces the session to be saved back to the session store, even if the session was never modified during the request.
	resave: true,
//Forces a session that is "uninitialized" to be saved to the store.
    saveUninitialized: true,
    secret: "qewhiugrwaiasgy"
  })
);

app.use("/", (req, res) => {
  var cookieValue;

  const check_cookie_set= req.body.box_cookie_set
  if (check_cookie_set){
    cookieValue = new Date().toString();
    res.cookie('cookie', cookieValue);
  }

  const check_cookie_del= req.body.box_cookie_del
  if (check_cookie_del){
    // req.cookies.cookie.maxAge = -1;
    res.clearCookie('cookie');
  }
  
  var sessionValue;

  const check_data= req.body.box_data
  if (check_data){
    sessionValue = new Date().toString();
    req.session.sessionValue = sessionValue;
  }

  const check_data2= req.body.box_data2
  if (check_data2){
    sessionValue = new Date().toString();
    req.session.sessionValue2 = sessionValue;
  }

  const check_usun = req.body.box_usun
  if (check_usun){
    delete req.session.sessionValue;
    delete req.session.sessionValue2;
  }

  res.render("index", {
  sessionValue: req.session.sessionValue,
  sessionValue2: req.session.sessionValue2,
  cookieValue: req.cookies.cookie,
  });
});



http.createServer(app).listen(3000);
