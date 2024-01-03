import ready from "../modules/ready.js"

function readRatingsFile(){
    const input = document.getElementById("ratingsCsv")

    const file = input.files[0]

    if ( file ){
        const reader = new FileReader()
        reader.onload = function(e){
            const content = e.target.result
            console.log(content)
            alert("Thanks!")
        }

        reader.readAsText(file)
    } else {
        alert("Please select a file")
    }
}

function main(){
    const submitButton = document.getElementById("ratingsCsvSubmit")
    submitButton.addEventListener("click", readRatingsFile)
}

ready(main)

