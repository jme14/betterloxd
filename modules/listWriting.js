
export default function writeListForDownload(data){
    let allLines = "Title,Year,URL,Description\n"

    for ( let i = 0 ; i < data.length ; i++ ){
        let betterLine = `"${data[i][1]}",${data[i][2]},${data[i][3]},\n`
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