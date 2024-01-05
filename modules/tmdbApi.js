import {config} from "./tmdbConfig.js"

const TMDB_URL = config.api_base_url
const TMDB_KEY = config.api_key
const IMG_URL = config.image_base_url

export async function getFilmByTitleAndYear(title, year){

    title = title.replace(/ /g,'+')
    try{

        const searchString = `${TMDB_URL}search/movie?query=${title}&api_key=${TMDB_KEY}`
        console.log(searchString)
        const response = await fetch(searchString)
        const responseData = await response.json()

        const data = responseData?.results

        for ( let i = 0 ; i < data.length ; i++){
            const yearFromData = data[i].release_date.split("-")[0]
            if (yearFromData === year.toString()){
                return data[i]
            }
        }
    } catch ( error ){
        console.log(error)
    }


    return null
}

export function getPosterPathFromTMDBData(tmdbData){
    const imgPath = `${IMG_URL}${tmdbData.poster_path}`

    return imgPath
}