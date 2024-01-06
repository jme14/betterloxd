import ready from "../modules/ready.js"
import {readLetterboxdHomemadeList} from "../modules/csvParsing.js"

import { getFilmByTitleAndYear } from "../modules/tmdbApi.js"
import { getPosterPathFromTMDBData } from "../modules/tmdbApi.js"

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
    writeListForDownload(data)
}


async function rankFilms(data){
    let newData = await recursiveQuickSort(data, 0, data.length-1)
    newData = newData.reverse()
    for ( let i = 0 ; i < newData.length ; i++ )
    {
        newData[i][0] = i+1
    }
    return newData 
}

// returns true if film1 better, false if film2 better
async function compareFilms (film1, film2){

    // populate images with poster from two films 
    const img1 = document.getElementById("film1img")
    const img2 = document.getElementById("film2img")


    const film1tmdb = await getFilmByTitleAndYear(film1[1],film1[2])
    const film2tmdb = await getFilmByTitleAndYear(film2[1],film2[2])

    img1.setAttribute("src", getPosterPathFromTMDBData(film1tmdb))
    img2.setAttribute("src", getPosterPathFromTMDBData(film2tmdb))

    // wait for user input 
    let result = await waitForChoice()

    // depending on user input, return true or false 
    if ( result === "Option1") return true
    return false
}

function waitForChoice() {
    return new Promise( (resolve) => {
        document.getElementById("film1button").addEventListener("click",()=>{
            resolve("Option1")
        })
        document.getElementById("film2button").addEventListener("click", ()=>{
            resolve("Option2")
        })
    },(reject) => {
        console.log(reject)   
    })
}

async function partition(data, low, high){
    function swap(data, e1index, e2index){
        let temp = data[e1index]
        data[e1index] = data[e2index]
        data[e2index] = temp

        return data
    }

    let pivot = data[high] 

    let lowSwapper = low-1

    for ( let highSwapper = low ; highSwapper < high ; highSwapper++){
        const pivotBetter = await compareFilms(pivot, data[highSwapper])
        if ( pivotBetter ){
            lowSwapper++
            data = swap(data, lowSwapper, highSwapper)
        }

    }

    data = swap(data, lowSwapper+1, high)

    return lowSwapper+1
}

async function recursiveQuickSort(data, low, high){
    if ( low < high ){
        try{
            let partitionIndex = await partition(data, low, high)
            data = await recursiveQuickSort(data, low, partitionIndex-1)
            data = await recursiveQuickSort(data, partitionIndex+1, high)
            return data
        } catch (error){
            console.log(error)
            return null
        }
    }
    return data
}

ready(main)

