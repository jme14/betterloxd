import { getFilmByTitleAndYear, getPosterPathFromTMDBData } from "./tmdbApi.js"

 function setAllImagesInDiv(theDiv, theSrc, theAlt){
    let allImages = theDiv.querySelectorAll("img")
    for ( let i = 0 ; i < allImages.length ; i++ ){
        allImages[i].setAttribute("src", theSrc)
        allImages[i].setAttribute("alt", theAlt)
    }

}

function movePoster(event, rowDiv, pivotImgSrc){


    let imgDiv = event.srcElement
    let imgInClickedDiv = null
    if ( imgDiv.tagName === "DIV"){
        imgInClickedDiv = imgDiv.querySelector("img")
    } else {
        imgInClickedDiv = imgDiv
        imgDiv = imgDiv.parentNode
    }

    let allImages = rowDiv.querySelectorAll("img")
    for ( let i = 0 ; i < allImages.length ; i++){
        if ( allImages[i].style.display !== "none" ){
            removePoster(allImages[i], pivotImgSrc)
        }
    }

    imgInClickedDiv.style.display = "block"
    showInfoButton(imgDiv)
}

function removePoster(img, pivotSrc){
    let imgId = img.id

    let position = imgId.split("-")[0]
    hideInfoButton(img.parentNode)
    if ( position === "middleFilmImg"){
        img.setAttribute("src", pivotSrc)
    } else {
        img.style.display = "none"
    }
}
function hideInfoButton(imgDiv){
    const currentInfoButton = imgDiv.nextElementSibling
    if ( !currentInfoButton.classList.contains("hiddenButton")){
        currentInfoButton.classList.add("hiddenButton")
    }

}

function showInfoButton(imgDiv){
    const infoButton = imgDiv.nextElementSibling
    if ( infoButton.classList.contains("hiddenButton")){
        infoButton.classList.remove("hiddenButton")
    }
}

export default async function addRow(containerContainer, originalDiv, filmRecord, number, pivotImgSrc){
    let clone = originalDiv.cloneNode(true)
    clone.id = `container-${number}`
    containerContainer.appendChild(clone)

    let imgList = clone.querySelectorAll("img")
    for ( let i = 0 ; i < imgList.length ; i++){
        let className = imgList[i].className
        imgList[i].id = `${className}-${number}`

        let parentDiv = imgList[i].parentNode
        let noscriptText = document.createElement("noscript")
        noscriptText.innerHTML = filmRecord[1]

        parentDiv.appendChild(noscriptText)

        if ( className !== "middleFilmImg"){
            parentDiv.addEventListener("click", (event) => movePoster(event, clone, pivotImgSrc))
        }
    }

    let tmdbData = await getFilmByTitleAndYear(filmRecord[1], filmRecord[2])
    setAllImagesInDiv(clone, getPosterPathFromTMDBData(tmdbData), filmRecord[1])
}

