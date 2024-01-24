import BetterloxdFilmRecord from "./betterloxdFilmRecord.js"

export function readLetterboxdHomemadeList(data){
    const papa = Papa.parse(data)

    const papaData = papa.data
    let returnArray = []

    for( let i = 1 ; i < papa.data.length ; i++ ){
        if ( papaData[i].length !== 8){
            continue
        } 
        let record = new BetterloxdFilmRecord(i, papaData[i][1], papaData[i][2], papaData[i][3], papaData[i][4], papaData[i][5], papaData[i][6])

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
        
        let newRecord = new BetterloxdFilmRecord(i, papaData[i][1], papaData[i][2], papaData[i][3], papaData[i][4], papaData[i][7], "NULL")

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

        let newRecord = new BetterloxdFilmRecord(i, papaData[i][1], papaData[i][2], papaData[i][3], papaData[i][4], "NULL", "NULL")
        returnArray.push(newRecord)
    }

    return returnArray
}