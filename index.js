const express = require("express")
const app = express()
const PORT = process.env.PORT || 3000

const dotenv = require('dotenv')
dotenv.config({path: __dirname+"/.env"})

// for serving static files 
// app.use is middleware 
app.use(express.static('public'))
app.use(express.static('public/pages'))

app.get("/tmdbData", (req, res) => {
    const tmdbData = {
        TMDB_URL: process.env.TMDB_URL,
        TMDB_KEY: process.env.TMDB_KEY,
        IMG_URL: process.env.IMG_URL
    }
    console.log(tmdbData)
    res.json(tmdbData)
})

app.listen(PORT, () => {
    console.log(`We going strong on port ${PORT}`)
})