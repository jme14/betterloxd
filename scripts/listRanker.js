import ready from "../modules/ready.js"
import {readLetterboxdHomemadeList} from "../modules/csvParsing.js"

import { getFilmByTitleAndYear } from "../modules/tmdbApi.js"
import { getPosterPathFromTMDBData } from "../modules/tmdbApi.js"

import QuickSortObject from "../modules/quickSortObject.js"

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


/* in here is where the ranking will take place */
async function useReadData(data) {
    data = await rankFilms(data)
}

async function rankFilms(data){
    console.log("We made it here!")
    let qs = new QuickSortObject(data, 0, data.length-1, "start")
    let qsPromise = qs.getCompletionPromise()
    qs.classMain()

    qsPromise.then( () => {

        const containerContainer = document.getElementById("containerContainer")
        while ( containerContainer.firstChild){
            containerContainer.removeChild(containerContainer.firstChild)
        }

        console.log("HERE IS YOUR COMPLETED LIST!")
        console.log(qs.data) 

        makeResultDisplay(qs.data)
    })


}

function makeResultDisplay (sortedData) {
    const containerContainer = document.getElementById("containerContainer")

    let listDiv = document.createElement("div")
    listDiv.id = "sortedListDiv"
    listDiv.classList.add("text-container")

    for ( let i = 0 ; i < sortedData.length ; i++ ){
        let nextHeader = document.createElement("h4")
        sortedData[i][0] = i+1
        nextHeader.innerHTML = `${sortedData[i][0]}) ${sortedData[i][1]} (${sortedData[i][2]})`

        listDiv.appendChild(nextHeader)
    }

    containerContainer.appendChild(listDiv)
}


ready(main)
