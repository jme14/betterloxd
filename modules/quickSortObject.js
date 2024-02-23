import { getFilmByTitleAndYear } from "./tmdbApi.js"
import { getPosterPathFromTMDBData} from "./tmdbApi.js"
import addRow from "./rankRowMaker.js"

import BetterloxdFilmRecord from "./betterloxdFilmRecord.js"

export default class QuickSortObject{

    constructor (data, low, high, source){

        while (data[data.length-1].length === 1){
            data.pop()
        }

        this.data = data

        this.low = low 
        this.high = high 
        this.pivotIndex = null

        this.sortedFilmsSet = new Set()

        this._resolveFunction = null
        this._recursiveCallsComplete = false
        this._recursiveCallsCompletePromise = new Promise(resolve => {
            this._resolveFunction = resolve
        });
        
    }

    markRecursiveCallsComplete(){
        this._recursiveCallsComplete = true

        if ( this._recursiveCallsCompletePromise) {
            this._resolveFunction(true)
            this._resolveFunction = null
        }
    }

    getCompletionPromise(){
        return this._recursiveCallsCompletePromise
    }

    async classMain(){
        if ( this.low > this.high || this.low === this.high ){
            this.markRecursiveCallsComplete()
            return
        } else {
            try{
                await this.populatePosters()
            } catch (error){
                console.log(error)
            }
        }
    }

    // STEP 1 
    async populatePosters(){
        let pivot = this.data[this.high]
        let originalDiv = document.getElementById("container-1")
        let containerContainer = document.getElementById("containerContainer")

        const shuffleButtonDiv = this.getShuffleButtonDiv()
        containerContainer.appendChild(shuffleButtonDiv)

        let pivotTMDB = await getFilmByTitleAndYear(pivot.getTitle(), pivot.getYear())
    
        for ( let i = this.low ; i < this.high ; i++ ){
            if ( this.data[i] !== undefined) {
                setTimeout(addRow, 1000, containerContainer, getPosterPathFromTMDBData(pivotTMDB), this.data[i], 2+(i-this.low))
            }
        }
        setTimeout(addCycleSubmitToPage, (this.high-this.low)+1000)

        let submitForCycle = document.createElement("button")
        submitForCycle.id = "cycleSubmitButton"
        submitForCycle.innerHTML = "Submit Cycle"
    
        let divForSubmitForCycle = document.createElement("div")
        divForSubmitForCycle.id = "cycleSubmitButtonDiv"
        divForSubmitForCycle.classList.add("button-container")

        divForSubmitForCycle.appendChild(submitForCycle)

        submitForCycle.addEventListener("click", async () => { 
            await this.calculateCycle()
            this.markRecursiveCallsComplete()
        })


        function addCycleSubmitToPage(){
            containerContainer.appendChild(divForSubmitForCycle)
        }
    }


    // STEP 2 : WAIT FOR USER INPUT 
    // STEP 3 : CALCULATE BASED ON USER INPUT 
    async calculateCycle(){
        function swap(data, e1index, e2index){

            let temp = data[e1index]
            data[e1index] = data[e2index]
            data[e2index] = temp

            return data
        }

        function compareFilms(index){
            // depending on where the image is displayed, this is the result 
            let leftPossibility = document.getElementById(`leftFilmImg-${index}`)
            if ( leftPossibility === null ) {
                throw ( new Error("Cannot find left possibility; element doesn't exist"))
            }
            if ( leftPossibility.style.display === "none"){
                return true
            }
            return false
        }

        let lowSwapper = this.low-1

        for ( let highSwapper = this.low ; highSwapper < this.high ; highSwapper++){
            const pivotBetter = compareFilms(highSwapper-this.low+2)
            if ( pivotBetter ){
                lowSwapper++
                this.data = swap(this.data, lowSwapper, highSwapper)
            }

        }
        this.data = swap(this.data, lowSwapper+1, this.high)
        this.pivotIndex = lowSwapper +1 
        await this.resetRows()
        
        return 
    }
    // STEP 4: REMOVE CONTENTS FROM DIV 
    async resetRows(){
        await this.resetRowsWithoutEvaluation()
        await this.nextCalls()

        return 
    }

    async resetRowsWithoutEvaluation(){
        let containerContainer = document.getElementById("containerContainer")
        while (containerContainer.firstChild){
            containerContainer.removeChild(containerContainer.firstChild)
        }
    }

    // STEP 5: WAIT FOR THE LEFT TO DO ITS THING 
    // STEP 6: WAIT FOR THE RIGHT TO DO ITS THING 
    async nextCalls(){
        this.leftCall = new QuickSortObject(this.data, this.low, this.pivotIndex-1, "left")
        let promiseLeft = this.leftCall.getCompletionPromise()
        await this.leftCall.classMain()
        await promiseLeft

        this.rightCall = new QuickSortObject(this.data, this.pivotIndex+1, this.high, "right")
        let promiseRight = this.rightCall.getCompletionPromise()
        await this.rightCall.classMain()
        await promiseRight

        return 

    }


    // OPTIONAL STEP: SHUFFLE DATA SO THAT THE PIVOT CHANGES
    shuffleData(){

        for ( let i = this.high ; i >= this.low ; i-- ){
            const j = Math.floor(Math.random()*(i+1))

            const temp = this.data[i]
            this.data[i] = this.data[j]
            this.data[j] = temp
        } 

        this.resetRowsWithoutEvaluation()
        this.populatePosters()
    }

    getShuffleButtonDiv(){

        if ( document.getElementById("shuffleButtonDiv") === null ){

            let shuffleButtonDiv = document.createElement("div")
            shuffleButtonDiv.classList.add("button-container")
            shuffleButtonDiv.id = "shuffleButtonDiv"

            // shuffle button
            let shuffleButton = document.createElement("button")
            shuffleButton.innerHTML = "Shuffle pivot"
            shuffleButton.addEventListener("click", () => this.shuffleData())
            shuffleButton.id = "shuffleButton"
            shuffleButtonDiv.appendChild(shuffleButton)

            return shuffleButtonDiv
        }

        return document.getElementById("shuffleButtonDiv")

    }
}