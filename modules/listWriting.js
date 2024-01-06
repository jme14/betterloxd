
export default function writeListForDownload(data){
    let allLines = "Position,Title,Year,URL,Rating,Watched Date,Description\n"

    for ( let i = 0 ; i < data.length ; i++ ){
        let betterLine = `${data[i][0]},"${data[i][1]}",${data[i][2]},${data[i][3]},${data[i][4]},${data[i][5]},"${data[i][6]}",\n`
        allLines = allLines + betterLine
    }

    // Create a Blob containing the CSV content
    const blob = new Blob([allLines], { type: 'text/csv' });

    // Create a link element
    const link = document.createElement('a');

    // Set the href attribute to a data URL representing the Blob
    link.href = window.URL.createObjectURL(blob);

    // Set the download attribute with the desired file name
    link.download = 'test.csv';

    // Append the link to the body
    document.body.appendChild(link);

    // Trigger a click event on the link to initiate the download
    link.click();

    // Remove the link from the DOM
    document.body.removeChild(link);


}