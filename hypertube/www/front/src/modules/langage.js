import translations from '../res/langages.json'

const DEFAULT_LANG = "english"
const available_langages = Object.keys(translations);

let lang = DEFAULT_LANG;

const change_langage = new_lang => {
    if (available_langages.includes(new_lang))
      lang = new_lang;
    else return false
    return true;
}

const translate = key => {
    return translations[lang][key]
}


export default {
  lang: lang,
  change_langage: change_langage,
  translate: translate
};