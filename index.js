const express = require("express")
const app = express()
const PORT = process.env.PORT || 3000

const dotenv = require('dotenv')
dotenv.config({path: __dirname+"/.env"})

// for serving static files 
// app.use is middleware 
app.use(express.static('public'))

app.set('view engine', 'ejs')
app.set('views', __dirname + "/public/pages")

app.get("/tmdbData", (req, res) => {
    const tmdbData = {
        TMDB_URL: process.env.TMDB_URL,
        TMDB_KEY: process.env.TMDB_KEY,
        IMG_URL: process.env.IMG_URL
    }
    console.log(tmdbData)
    res.json(tmdbData)
})

app.get("/", (req, res) => {
    res.render("index.ejs", {pageTitle: "Welcome to Betterloxd!"})
})
app.get("/listRanker", (req, res) => {
    res.render("listRanker.ejs", {pageTitle: "Rank a Betterloxd List!"})
})
app.get("/ratingRangeListMaker", (req, res) => {
    res.render("ratingRangeListMaker.ejs", {pageTitle: "Rating Range List Maker!"})
})
app.get("/yearWatchedListMaker", (req, res) => {
    res.render("yearWatchedListMaker.ejs", {pageTitle: "Year End List Maker!"})
})

app.listen(PORT, () => {
    console.log(`We going strong on port ${PORT}`)
})