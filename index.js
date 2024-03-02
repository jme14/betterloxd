const express = require("express")
const app = express()
const port = 3000

const path = require("path")

// for serving static files 
// app.use is middleware 
app.use(express.static('public'))
app.use(express.static('public/pages'))

app.get("/", (req,res) => {
    res.send("Hello!")
})


app.listen(port, () => {
    console.log(`We going strong on port ${port}`)
})