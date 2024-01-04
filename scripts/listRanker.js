import ready from "../modules/ready.js"
import {readLetterboxdHomemadeList} from "../modules/csvParsing.js"

import writeListForDownload from "../modules/listWriting.js"

function readListFile(){
    const input = document.getElementById("rankCsv")

    const file = input.files[0]

    if ( file ){
        const reader = new FileReader()
        reader.onload = function(e){
            const content = e.target.result
            useReadData(readLetterboxdHomemadeList(content))
        }

        reader.readAsText(file)
    } else {
        alert("Please select a file")
    }
}

function main(){
    const submitButton = document.getElementById("rankCsvSubmit")
    submitButton.addEventListener("click", readListFile)

}

function useReadData(data){

    for ( let i = 0 ; i < data.length; i++ ){
        console.log(data[i])
    }
    
    //writeListForDownload(data)
}

ready(main)

