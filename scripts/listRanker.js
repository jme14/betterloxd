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

        document.getElementById("poster-title-container").remove()
        document.getElementById("file-submission-container").remove()

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
        sortedData[i].setRank(i+1)
        nextHeader.innerHTML = `${sortedData[i].getRank()}) ${sortedData[i].getTitle()} (${sortedData[i].getYear()})`

        listDiv.appendChild(nextHeader)
    }


    let onRankedListDownload = function(inReverse){
        if ( inReverse) {
            console.log("You want it in reverse!")
            sortedData = sortedData.reverse()

            for ( let i = 1 ; i <= sortedData.length ; i++ ){
                sortedData[i-1].setRank(i)
            }

            writeListForDownload(sortedData)

        } else {
            console.log("You want it in order!")
            writeListForDownload(sortedData)
        }
    }

    let downloadListDiv = document.createElement("div")
    downloadListDiv.id = "downloadRankedListDiv"
    downloadListDiv.classList.add("rankedListButtonDiv")


    let downloadInOrder = document.createElement("button")
    downloadInOrder.id = "downloadInOrderButton"
    downloadInOrder.innerHTML = "Download List In Order"
    downloadInOrder.addEventListener("click", () => onRankedListDownload(false))

    let downloadReverseOrder = document.createElement("button")
    downloadReverseOrder.id = "downloadReverseOrderButton"
    downloadReverseOrder.innerHTML = "Download List In Reverse Order"
    downloadReverseOrder.addEventListener("click", () => onRankedListDownload(true))


    downloadListDiv.appendChild(downloadInOrder)
    downloadListDiv.appendChild(downloadReverseOrder)

    containerContainer.appendChild(listDiv)
    containerContainer.appendChild(downloadListDiv)
}


ready(main)
