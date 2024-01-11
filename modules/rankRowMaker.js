import { getFilmByTitleAndYear, getPosterPathFromTMDBData } from "./tmdbApi.js"

 function setAllImagesInDiv(theDiv, theSrc){
    let allImages = theDiv.querySelectorAll("img")
    for ( let i = 0 ; i < allImages.length ; i++ ){
        allImages[i].setAttribute("src", theSrc)
    }

}

function movePoster(event, rowDiv, pivotImgSrc){


    let imgDiv = event.srcElement
    let imgInClickedDiv = null
    if ( imgDiv.tagName === "DIV"){
        imgInClickedDiv = imgDiv.querySelector("img")
    } else {
        imgInClickedDiv = imgDiv
    }

    let allImages = rowDiv.querySelectorAll("img")
    for ( let i = 0 ; i < allImages.length ; i++){
        if ( allImages[i].style.display !== "none" ){
            removePoster(allImages[i], pivotImgSrc)
        }
    }

    console.log(imgInClickedDiv)
    imgInClickedDiv.style.display = "block"
}

function removePoster(img, pivotSrc){
    let imgId = img.id

    let position = imgId.split("-")[0]
    if ( position === "middleFilmImg"){
        img.setAttribute("src", pivotSrc)
    } else {
        img.style.display = "none"
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

        if ( className !== "middleFilmImg"){
            let parentDiv = imgList[i].parentNode;
            parentDiv.addEventListener("click", (event) => movePoster(event, clone, pivotImgSrc))
        }
    }
    console.log(filmRecord)

    let tmdbData = await getFilmByTitleAndYear(filmRecord[1], filmRecord[2])
    setAllImagesInDiv(clone, getPosterPathFromTMDBData(tmdbData))
}

