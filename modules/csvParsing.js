

export function readLetterboxdHomemadeList(data){
    const papa = Papa.parse(data)

    const papaData = papa.data
    let returnArray = []

    for( let i = 1 ; i < papa.data.length ; i++ ){
        if ( papaData[i].length !== 8){
            continue
        } 
        let record = []

        record.push(i) //position
        record.push(papaData[i][1]) //title 
        record.push(papaData[i][2]) //year 
        record.push(papaData[i][3]) //URL
        record.push(papaData[i][4]) //rating
        record.push(papaData[i][5]) //watched date
        record.push(papaData[i][6]) //description

        returnArray.push(record)
    }

    return returnArray
}


export function readLetterboxdDataDiary(data, removeRewatches){

    const papa = Papa.parse(data)

    const papaData = papa.data
    let realData = []
    console.log(papaData)

    for ( let i = 1 ; i < data.length ; i++ ){
        if ( papaData[i] === undefined || papaData[i].length !== 8) continue

        if ( removeRewatches === true ){
            if ( papaData[i][5] === "Yes")
            continue
        }
        
        let newRecord = [];

        newRecord.push(i+1) // position 
        newRecord.push(papaData[i][1]) // title  
        newRecord.push(papaData[i][2]) // year 
        newRecord.push(papaData[i][3]) // url 
        newRecord.push(papaData[i][4]) // rating 
        newRecord.push(papaData[i][7]) // watchedDate
        newRecord.push("NULL") // description 

        realData.push(newRecord)
    }
    return realData
}

export function readLetterboxdDataRatings(data){
    const papa = Papa.parse(data)

    const papaData = papa.data

    let returnArray = [];

    for ( let i = 1 ; i < papaData.length ; i++ ){
        if ( papaData[i].length !== 5) continue

        let returnArrayElement = []
        returnArrayElement.push(i)  // position 
        returnArrayElement.push(papaData[i][1]) //title 
        returnArrayElement.push(papaData[i][2]) //year
        returnArrayElement.push(papaData[i][3]) //url 
        returnArrayElement.push(papaData[i][4]) //rating 
        returnArrayElement.push("NULL") //watchedDate
        returnArrayElement.push("NULL") //description

        returnArray.push(returnArrayElement)
    }

    return returnArray
}