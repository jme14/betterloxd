import ready from "../modules/ready.js"
import {readLetterboxdDataRatings} from "../modules/csvParsing.js"

import writeListForDownload from "../modules/listWriting.js"

function readRatingsFile(){


    const lowerBound = document.getElementById("low").value
    const higherBound = document.getElementById("high").value

    if ( lowerBound > higherBound ){
        alert("Select a higher value greater than or equal to the low value")
        return;
    }

    const input = document.getElementById("ratingsCsv")
    const file = input.files[0]

    if ( file ){
        const reader = new FileReader()
        reader.onload = function(e){
            const content = e.target.result
            useReadData(readLetterboxdDataRatings(content), lowerBound, higherBound)
        }

        reader.readAsText(file)
    } else {
        alert("Please select a file")
    }
}

function main(){
    const submitButton = document.getElementById("ratingsCsvSubmit")
    submitButton.addEventListener("click", readRatingsFile)


    const lowLabel = document.getElementById('low')
    lowLabel.addEventListener('input', updateLowValue);

    const highLabel = document.getElementById('high')
    highLabel.addEventListener('input', updateHighValue);

    function updateLowValue() {
        const lowValSpan = document.getElementById('lowValue')

        if ( lowLabel.value % 1 !== 0 ){
            lowValSpan.textContent = lowLabel.value;
        } else {
            lowValSpan.textContent = lowLabel.value + ".0"
        }

    }

    function updateHighValue() {
        const highValSpan = document.getElementById('highValue')

        if ( highLabel.value % 1 !== 0 ){
            highValSpan.textContent = highLabel.value;
        } else {
            highValSpan.textContent = highLabel.value + ".0"
        }
    }
}

function useReadData(data, lowerBound, higherBound){

    function isInRange(record){
        return (record.getRating() >= lowerBound && record.getRating() <= higherBound)
    }

    data = data.filter(isInRange)

    for ( let i = 0 ; i < data.length; i++ ){
        console.log(data[i])
    }
    
    writeListForDownload(data)
}

ready(main)

