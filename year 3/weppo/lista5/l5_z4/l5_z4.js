const http = require("http");
const express = require("express");
const bodyParser = require("body-parser");
const app = express();

const { check, validationResult } = require("express-validator");

app.set("view engine", "ejs");

app.set("views", "./views");

app.use(express.urlencoded({ extended: true }));

// bodyParses umożliwia przychodzącym żądaniom rozpatrzenie ich przez req.body. extended umożliwia przesyłanie zagnieżdżonych obiektów
app.use(bodyParser.urlencoded({ extended: true }));

app.get("/", (req, res) => {
  res.render("form");
});

app.post(
  "/print",
  [
    check("name").notEmpty(),
    check("surname").notEmpty(),
    check("classes").notEmpty(),
    check("exercise1")
    // pozwala na puste pole
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise2")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise3")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise4")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise5")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise6")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise7")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise8")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise9")
      .optional({ checkFalsy: true })
      .isInt(),
    check("exercise10")
      .optional({ checkFalsy: true })
      .isInt()
  ],
  (req, res) => {
    const {
      name,
      surname,
      classes,
      exercise1,
      exercise2,
      exercise3,
      exercise4,
      exercise5,
      exercise6,
      exercise7,
      exercise8,
      exercise9,
      exercise10
    } = req.body;

    const errors = validationResult(req);
    if (!errors.isEmpty()) {
      return res.redirect("/");
    }

    res.render("print", {
      name,
      surname,
      classes,
      exercises: [
        exercise1 || 0,
        exercise2 || 0,
        exercise3 || 0,
        exercise4 || 0,
        exercise5 || 0,
        exercise6 || 0,
        exercise7 || 0,
        exercise8 || 0,
        exercise9 || 0,
        exercise10 || 0
      ]
    });
  }
);

http.createServer(app).listen(3000);
console.log("started");
