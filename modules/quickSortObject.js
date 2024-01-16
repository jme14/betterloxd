import { getFilmByTitleAndYear } from "./tmdbApi.js"
import { getPosterPathFromTMDBData} from "./tmdbApi.js"
import addRow from "./rankRowMaker.js"

export default class QuickSortObject{

    constructor (data, low, high, source){

        console.log(data)
        console.log(low)
        console.log(high)


        // this is kind of stupid, change this later 
        while (data[data.length-1].length === 1){
            console.log("POP POP")
            data.pop()
        }

        this.data = data

        this.low = low 
        this.high = high 
        this.pivotIndex = null

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
            console.log("Don't worry! I'm going to mark this recursive call as complete!")
            this.markRecursiveCallsComplete()
            return
        } else {
            console.log("The above are absolutely not the same number heehee!")
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

        let pivotTMDB = await getFilmByTitleAndYear(pivot[1], pivot[2])
        document.getElementById("middleFilmImg-1").setAttribute("src", getPosterPathFromTMDBData(pivotTMDB))
        document.getElementById("middleFilmImg-1").setAttribute("alt", pivotTMDB[1])
    
        for ( let i = this.low ; i < this.high ; i++ ){
            if ( this.data[i] !== undefined) {
                addRow(containerContainer,originalDiv, this.data[i], 2+(i-this.low), getPosterPathFromTMDBData(pivotTMDB))
            }
        }
    
        let submitForCycle = document.createElement("button")
        submitForCycle.id = "cycleSubmitButton"
        submitForCycle.innerHTML = "Submit Cycle"
    
        let divForSubmitForCycle = document.createElement("div")
        divForSubmitForCycle.id = "cycleSubmitButtonDiv"
        divForSubmitForCycle.classList.add("button-container")
    
        divForSubmitForCycle.appendChild(submitForCycle)


        containerContainer.appendChild(divForSubmitForCycle)
    
        document.getElementById("cycleSubmitButton").addEventListener("click", async () => { 
            await this.calculateCycle()
            this.markRecursiveCallsComplete()
        })

        console.log(`Data has a length of ${this.data.length}`)
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
                console.log(document.getElementById("containerContainer"))
                console.log(index)
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
        let containerContainer = document.getElementById("containerContainer")
        let clone = document.getElementById("container-1").cloneNode(true)

        let shuffleButtonDiv = document.getElementById("shuffleButtonDiv")
        shuffleButtonDiv.remove()

        while (containerContainer.firstChild){
            containerContainer.removeChild(containerContainer.firstChild)
        }


        containerContainer.appendChild(clone)
        await this.nextCalls()

        return 
    }

    // STEP 5: WAIT FOR THE LEFT TO DO ITS THING 
    // STEP 6: WAIT FOR THE RIGHT TO DO ITS THING 
    async nextCalls(){
        this.leftCall = new QuickSortObject(this.data, this.low, this.pivotIndex-1, "left")
        let promiseLeft = this.leftCall.getCompletionPromise()
        await this.leftCall.classMain()
        console.log(promiseLeft)
        await promiseLeft

        this.rightCall = new QuickSortObject(this.data, this.pivotIndex+1, this.high, "right")
        let promiseRight = this.rightCall.getCompletionPromise()
        await this.rightCall.classMain()
        console.log(promiseRight)
        await promiseRight

        console.log("Returning!")
        return 

    }


    // OPTIONAL STEP: SHUFFLE DATA SO THAT THE PIVOT CHANGES
    shuffleData(){
        console.log(`Shuffling data, which is of length ${this.data.length}`)
        for ( let i = this.data.length-1 ; i > 0 ; i-- ){
            const j = Math.floor(Math.random()*(i+1))

            const temp = this.data[i]
            this.data[i] = this.data[j]
            this.data[j] = temp
        } 
        console.log(`Done shuffling data, which is now of length ${this.data.length}`)

        this.resetRows()
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