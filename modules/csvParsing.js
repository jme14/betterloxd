
export function readLetterboxdDataRatings(data){
    data = data.split("\n")

    for ( let i = 1 ; i < data.length ; i++ ){
        if ( /"/.test(data[i])){ //if quotation marks exist, treat differently
            const getTitle = data[i].split("\"")
            let tempData = [] 

            const beforeTitleSplit = getTitle[0].split(",")
            let afterTitleSplit = getTitle[2].split(",")

            for ( let j = 0 ; j < beforeTitleSplit.length-1 ; j++ ){
                tempData.push(beforeTitleSplit[j])
            }
            tempData.push(getTitle[1])
            for ( let j = 1 ; j < afterTitleSplit.length ; j++ ){
                tempData.push(afterTitleSplit[j])
            }
            data[i] = tempData
        }
        else{
            const insertionContent = data[i].split(",")
            if (insertionContent.length < 5) continue
            data[i] = insertionContent
        }
        data[i][4] = data[i][4].split("\r")[0]
    }

    data=data.slice(1)
    while(data[data.length-1].length !== 5){
        data.pop()
    }

    let realData = []

    for ( let i = 0 ; i < data.length ; i++ ){
        let newRecord = [];

        newRecord.push(i+1) // position 
        newRecord.push(data[i][1]) // title  
        newRecord.push(data[i][2]) // year 
        newRecord.push(data[i][3]) // url 
        newRecord.push(data[i][4]) // rating 

        realData.push(newRecord)
    }

    return realData
}