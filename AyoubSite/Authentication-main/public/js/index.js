/*=============== SHOW HIDE PASSWORD LOGIN ===============*/
const passwordAccess = (loginPass, loginEye) => {
    const input = document.getElementById(loginPass),
        iconEye = document.getElementById(loginEye)

    iconEye.addEventListener('click', () => {
        // Change password to text
        input.type === 'password' ? input.type = 'text'
            : input.type = 'password'

        // Icon change
        iconEye.classList.toggle('ri-eye-fill')
        iconEye.classList.toggle('ri-eye-off-fill')
    })
}
passwordAccess('password', 'loginPassword')

/*=============== SHOW HIDE PASSWORD CREATE ACCOUNT ===============*/
const passwordRegister = (loginPass, loginEye) => {
    const input = document.getElementById(loginPass),
        iconEye = document.getElementById(loginEye)

    iconEye.addEventListener('click', () => {
        // Change password to text
        input.type === 'password' ? input.type = 'text'
            : input.type = 'password'

        // Icon change
        iconEye.classList.toggle('ri-eye-fill')
        iconEye.classList.toggle('ri-eye-off-fill')  
    })
}
passwordRegister('passwordCreate', 'loginPasswordCreate')

/*=============== SHOW HIDE LOGIN & CREATE ACCOUNT ===============*/
const loginAcessRegister = document.getElementById('loginAccessRegister'),
    buttonRegister = document.getElementById('loginButtonRegister'),
    buttonAccess = document.getElementById('loginButtonAccess')

buttonRegister.addEventListener('click', () => {
    loginAcessRegister.classList.add('active')
})

buttonAccess.addEventListener('click', () => {
    loginAcessRegister.classList.remove('active')
})

document.addEventListener("DOMContentLoaded", () => {
    const form = document.querySelector("form");
    const loginButton = document.querySelector(".login__button");
    const loginSection = document.querySelector(".login");
  
    if (form && loginButton && loginSection) {
      form.addEventListener("submit", function (e) {
        e.preventDefault(); // Empêche la soumission directe
  
        // Ajoute la classe de chargement
        loginButton.classList.add("loading");
  
        // Attends un peu pour l'effet
        setTimeout(() => {
          loginSection.classList.add("fade-out");
  
          // Simule la redirection ou le traitement après un court délai
          setTimeout(() => {
            // Redirection simulée (à adapter selon ton besoin réel)
            window.location.href = "site.html";
          }, 700);
        }, 800);
      });
    }
  });