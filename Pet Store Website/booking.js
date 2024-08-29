window.onload = init;

function init() {
   document.forms[0].onsubmit = function () {
      if (this.checkValidity()) alert("Thanks for booking! Hairy Paws will contact you soon.");
      window.close();
      return false;
   }

   //THIS IS FOR CAT DOG SWITCH IMAGE
   document.getElementById("cat").onclick = turnOnCat;
   document.getElementById("dog").onclick = turnOnDog;

   //THIS IS FOR SWITCH OPTION VALUE
   // Get references to the select elements
   const radioButtons = document.querySelectorAll('input[type="radio"]');
   const firstSelect = document.getElementById('group');
   const secondSelect = document.getElementById('category');
   const thirdSelect = document.getElementById('size');

   // Define options for the second select element based on the selection in the first select element
   const optionsByGroup = {
      basic: [
         { value: 'basicGrooming', display: 'Basic Grooming' }
      ],
      addOn: [
         { value: 'spa2', display: 'Spa - 2 sessions' },
         { value: 'spa4', display: 'Spa - 4 sessions' },
         { value: 'stylingData', display: 'Styling Data' },
         { value: 'undercoatA', display: 'Undercoat - A' },
         { value: 'undercoatB', display: 'Undercoat - B' },
         { value: 'undercoatC', display: 'Undercoat - C' },
         { value: 'undercoatD', display: 'Undercoat - D' },
         { value: 'conditioner', display: 'Conditioner' },
         { value: 'shampoo', display: 'Premium Shampoo' }
      ],
   };

   // Function to update the second select element based on the selected fruit
   function updateSecondSelect() {
      const selectedGroup = firstSelect.value;
      const options = optionsByGroup[selectedGroup];

      // Clear the current options in the second select
      secondSelect.innerHTML = '';

      // Add new options based on the selected fruit
      for (const option of options) {
         const optionElement = document.createElement('option');
         optionElement.value = option.value;
         optionElement.textContent = option.display;
         secondSelect.appendChild(optionElement);
      }
   }

   function updateThirdSelect() {
      for (const radioButton of radioButtons) {
         if (radioButton.checked) {
            const petType = radioButton.value;
            switch (petType) {
               case 'cat':
                  thirdSelect.innerHTML = '<option value="M">M</option><option value="L">L</option>';
                  break;
               case 'dog':
                  thirdSelect.innerHTML = '<option value="S">S</option><option value="M">M</option><option value="L">L</option><option value="XL">XL</option>';
                  break;
            }
         }
      }
   }


   // Add an event listener to the first select element to update the second select element
   firstSelect.addEventListener('change', updateSecondSelect);
   for (const radioButton of radioButtons) {
      radioButton.addEventListener('change', updateThirdSelect);
   }

   // Initial call to populate the second select based on the default selected option
   updateSecondSelect();
   updateThirdSelect();
}

function turnOnCat() {
   document.getElementById("pet_circle_cat").style.display = "block";
   document.getElementById("pet_circle_dog").style.display = "none";
   document.getElementById("cat").style.backgroundColor = "#a6f1c1";
   document.getElementById("dog").style.backgroundColor = "white";
}

function turnOnDog() {
   document.getElementById("pet_circle_cat").style.display = "none";
   document.getElementById("pet_circle_dog").style.display = "block";
   document.getElementById("dog").style.backgroundColor = "#a6f1c1";
   document.getElementById("cat").style.backgroundColor = "white";
}
