// app.js
var http = require('http');
var express = require('express');

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
	var combo1 = {
		name: 'combo1',
		options: [{
				name: 'box1',
				text: 'element 1'
			},
			{
				name: 'box2',
				text: 'element 2'
			},
			{
				name: 'box3',
				text: 'element 3'
			}
		]
	};
	var combo2 = {
		name: 'combo2',
		options: [{
				name: 'box4',
				text: 'element 4'
			},
			{
				name: 'box5',
				text: 'element 5'
			},
			{
				name: 'box6',
				text: 'element 6'
			}
		]
	}
	res.render('index', {
		combo1,
		combo2
	});
});

http.createServer(app).listen(3000);