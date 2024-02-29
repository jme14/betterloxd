export default function writeListForDownload(data){
    let allLines = "Position,Title,Year,URL,Rating,Watched Date,Description\n"
    
    for ( let i = 0 ; i < data.length ; i++ ){
        let betterLine = `${data[i].getRank()},"${data[i].getTitle()}",${data[i].getYear()},${data[i].getUrl()},${data[i].getRating()},${data[i].getWatchedDate()},"${data[i].getDescription()}",\n`
        allLines = allLines + betterLine
    }

    const blob = new Blob([allLines], { type: 'text/csv' });

    const link = document.createElement('a');
    link.innerHTML = "Download .csv"
    link.href = window.URL.createObjectURL(blob);

    let fileName = null
    try{
        fileName = document.getElementById("fileNameInput").value
        link.download = `${fileName}.csv`;

    } catch (e){
        link.download = `betterloxdList.csv`

    }


    link.setAttribute("style", "color: white")

    const linkDiv = document.getElementById("downloadLinkDiv")
    while(linkDiv.firstChild) {
        linkDiv.removeChild(linkDiv.lastChild)
    }

    linkDiv.appendChild(link);



}