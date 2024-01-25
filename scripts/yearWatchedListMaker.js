import ready from "../modules/ready.js"
import {readLetterboxdDataDiary} from "../modules/csvParsing.js"

import writeListForDownload from "../modules/listWriting.js"

function readDiaryFile(){
    const input = document.getElementById("diaryCsv")

    const file = input.files[0]

    if ( file ){
        const reader = new FileReader()
        reader.onload = function(e){
            const content = e.target.result
            useReadData(readLetterboxdDataDiary(content, true))
        }

        reader.readAsText(file)
    } else {
        alert("Please select a file")
    }
}

function main(){
    const submitButton = document.getElementById("diaryCsvSubmit")
    submitButton.addEventListener("click", readDiaryFile)

}

function useReadData(data){

    const yearSubmitted = document.getElementById("yearPicker").value

    function isInRange(record){
        const year = record.getWatchedDate().split("-")[0]
        return year === yearSubmitted
    }

    data = data.filter(isInRange)

    for ( let i = 0 ; i < data.length; i++ ){
        console.log(data[i])
    }
    
    writeListForDownload(data)
}

ready(main)

